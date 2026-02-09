package pl.fc.auth;

import android.app.Activity;
import android.os.CancellationSignal;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.credentials.Credential;
import androidx.credentials.CredentialManager;
import androidx.credentials.CredentialManagerCallback;
import androidx.credentials.GetCredentialRequest;
import androidx.credentials.GetCredentialResponse;
import androidx.credentials.CustomCredential;
import androidx.credentials.exceptions.GetCredentialException;

import com.google.android.libraries.identity.googleid.GetGoogleIdOption;
import com.google.android.libraries.identity.googleid.GoogleIdTokenCredential;
import com.google.android.libraries.identity.googleid.GoogleIdTokenParsingException;

import java.util.concurrent.Executor;
import java.util.concurrent.Executors;

public final class QtGoogleAuth {
    private static final String TAG = "QtGoogleAuth";


    public static native void nativeOnGoogleIdToken(String token);
    public static native void nativeOnGoogleError(String message);

    public static void signIn(Activity activity, String webClientId, boolean filterAuthorizedAccounts) {
        CredentialManager cm = CredentialManager.create(activity);

        GetGoogleIdOption googleIdOption =
                new GetGoogleIdOption.Builder()
                        .setFilterByAuthorizedAccounts(filterAuthorizedAccounts)
                        .setServerClientId(webClientId)
                        .build();

        GetCredentialRequest request =
                new GetCredentialRequest.Builder()
                        .addCredentialOption(googleIdOption)
                        .build();

        CancellationSignal cancelSignal = new CancellationSignal();
        Executor executor = Executors.newSingleThreadExecutor();

        cm.getCredentialAsync(
                activity,
                request,
                cancelSignal,
                executor,
                new CredentialManagerCallback<GetCredentialResponse, GetCredentialException>() {
                    @Override
                    public void onResult(GetCredentialResponse result) {
                        handleResult(result);
                    }

                    @Override
                    public void onError(@NonNull GetCredentialException e) {
                        Log.e(TAG, "getCredentialAsync error", e);
                        nativeOnGoogleError("GetCredentialException: " + e.getMessage());
                    }
                }
        );
    }

    
    private static void handleResult(GetCredentialResponse result) {
        Credential credential = result.getCredential();

        if (credential instanceof CustomCredential) {
            CustomCredential cc = (CustomCredential) credential;

            if (GoogleIdTokenCredential.TYPE_GOOGLE_ID_TOKEN_CREDENTIAL.equals(cc.getType())) {
                try {
                    GoogleIdTokenCredential googleCred =
                            GoogleIdTokenCredential.createFrom(cc.getData());
                    String idToken = googleCred.getIdToken();

                    nativeOnGoogleIdToken(idToken);

                } catch (Exception e) {
                    nativeOnGoogleError("Token parse error: " + e.getClass().getSimpleName() + ": " + e.getMessage());
                }
                return;
            }
        }

        nativeOnGoogleError("Unexpected credential type: " + credential.getClass().getName());
    }

}